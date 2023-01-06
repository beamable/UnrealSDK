// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackend/ResponseCache/BeamResponseCache.h"



void UBeamResponseCache::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CoreSettings = GetDefault<UBeamCoreSettings>();
}

void UBeamResponseCache::Deinitialize()
{
	Super::Deinitialize();
}

bool UBeamResponseCache::TryHitResponseCache(const TScriptInterface<IBeamBaseRequestInterface> ReqDataObject, const TUnrealRequestPtr ReqObject, const UObject* CallingContext, FString& OutResponse)
{
	const FString ReqBody = FString::FromBlob(ReqObject->GetContent().GetData(), ReqObject->GetContentLength());
	const FString ReqHeader = ReqObject->GetHeader(UBeamBackend::HEADER_AUTHORIZATION);
	const FString ReqRoute = ReqObject->GetURL();

	// Get the Request Type
	const auto ReqType = ReqDataObject->GetRequestType();

	// Get which level of cache is currently responsible for cache-ing this request.
	TEnumAsByte<EBeamCacheHierarchyLevel> InCacheLevel;
	const auto Config = FindCacheConfig(ReqType, CallingContext, InCacheLevel);

	// Check if I should invalidate the cache and do it if I have too.
	if (ShouldInvalidateResponseCache(ReqDataObject, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody))
	{
		InvalidateCacheAtHierarchyLevel(InCacheLevel, ResponseStringCache, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody);
		InvalidateCacheAtHierarchyLevel(InCacheLevel, CacheHitTimestamps, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody);
		OutResponse = TEXT("");
		return false;
	}

	// Otherwise, we try to grab the data from the cache
	if (TryGetFromCacheHierarchy(InCacheLevel, ResponseStringCache, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody, OutResponse))
	{
		// If we are in a time mode configuration, we update the CacheTimestamp so that we know when we need to invalidate it or check it for invalidation.
		if (Config.Mode == Time || Config.Mode == ConditionalOnTime)
		{
			UpdateCacheAtHierarchyLevel(InCacheLevel, CacheHitTimestamps, FDateTime::UtcNow(), ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody);
		}
		return true;
	}

	// If we don't have the data in the cache, we simply return false.
	OutResponse = TEXT("");
	return false;
}

void UBeamResponseCache::UpdateResponseCache(FRequestType ReqType, const UObject* CallingContext, const TUnrealRequestPtr ReqObject, FString ResponseAsString)
{
	const FString ReqBody = FString::FromBlob(ReqObject->GetContent().GetData(), ReqObject->GetContentLength());
	const FString ReqHeader = ReqObject->GetHeader(UBeamBackend::HEADER_AUTHORIZATION);
	const FString ReqRoute = ReqObject->GetURL();
	
	// Get which level of cache is currently responsible for cache-ing this request.
	TEnumAsByte<EBeamCacheHierarchyLevel> InCacheLevel;
	const auto Config = FindCacheConfig(ReqType, CallingContext, InCacheLevel);

	// If we don't have to cache it, we just don't.
	if (Config.Mode == Disabled)
		return;

	// Update the Response cache.
	UpdateCacheAtHierarchyLevel(InCacheLevel, ResponseStringCache, ResponseAsString, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody);

	// Update the CacheTimestamp so that we know when we need to invalidate it or check it for invalidation.
	if (Config.Mode == Time || Config.Mode == ConditionalOnTime)
	{
		UpdateCacheAtHierarchyLevel(InCacheLevel, CacheHitTimestamps, FDateTime::UtcNow(), ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody);
	}
}

void UBeamResponseCache::InvalidateAll()
{
	ResponseStringCache.GlobalCache.Reset();
	ResponseStringCache.RequestTypeCache.Reset();
	ResponseStringCache.CallingContextCache.Reset();
	ResponseStringCache.CallsiteCache.Reset();

	CacheHitTimestamps.GlobalCache.Reset();
	CacheHitTimestamps.RequestTypeCache.Reset();
	CacheHitTimestamps.CallingContextCache.Reset();
	CacheHitTimestamps.CallsiteCache.Reset();
}

void UBeamResponseCache::ClearNonGlobalConfigs()
{
	RequestTypeCacheConfig.Reset();
	CallingContextCacheConfig.Reset();
	CallsiteCacheConfig.Reset();

	ResponseStringCache.RequestTypeCache.Reset();
	ResponseStringCache.CallingContextCache.Reset();
	ResponseStringCache.CallsiteCache.Reset();
	
	CacheHitTimestamps.RequestTypeCache.Reset();
	CacheHitTimestamps.CallingContextCache.Reset();
	CacheHitTimestamps.CallsiteCache.Reset();
}

bool UBeamResponseCache::ShouldInvalidateResponseCache(const TScriptInterface<IBeamBaseRequestInterface> ReqObject, FRequestType ReqType, const UObject* CallingContext,
                                                       FString ReqHeader, FString ReqRoute, FString ReqBody) const
{
	// Get which level of cache is currently responsible for cache-ing this request.
	TEnumAsByte<EBeamCacheHierarchyLevel> InCacheLevel;
	const auto Config = FindCacheConfig(ReqType, CallingContext, InCacheLevel);
	switch (Config.Mode)
	{
	case Disabled:
		{
			// If cache is disabled for this request, we simply always invalidate.
			return true;
		}
	case Time:
		{
			// See how long ago did we hit the cache.
			FDateTime LastHitTime;
			TryGetFromCacheHierarchy(InCacheLevel, CacheHitTimestamps, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody, LastHitTime);
			const auto Now = FDateTime::UtcNow();
			const auto Diff = Now - LastHitTime;
			const auto Seconds = Diff.GetTotalSeconds();
			const auto TimeToInvalidation = Config.Time;

			// If its over the time, we invalidate. Otherwise, we don't.
			return Seconds >= TimeToInvalidation;
		}
	case ConditionalOnTime:
		{
			// See how long ago did we hit the cache.
			FDateTime LastHitTime;
			TryGetFromCacheHierarchy(InCacheLevel, CacheHitTimestamps, ReqType, CallingContext, ReqHeader, ReqRoute, ReqBody, LastHitTime);			
			const auto Now = FDateTime::UtcNow();
			const auto Diff = Now - LastHitTime;
			const auto SecondsDiff = Diff.GetTotalSeconds();
			const auto TimeToCheck = Config.Time;

			// If its over the time and the conditional is bound, we run the conditional. Otherwise, we DON'T invalidate.
			return SecondsDiff >= TimeToCheck && Config.ShouldInvalidateCacheDelegate.IsBound() ? Config.ShouldInvalidateCacheDelegate.Execute(ReqObject) : false;
		}
	default:
		{
			return true;
		}
	}
}

FBeamCacheConfig UBeamResponseCache::FindCacheConfig(FRequestType ReqType, const UObject* CallingContext, TEnumAsByte<EBeamCacheHierarchyLevel>& OutLevel) const
{
	// First, we prioritize this request type from this calling context.
	const auto Callsite = FBeamCachedRequestCallsite{ReqType, CallingContext};
	if (CallingContext && CallsiteCacheConfig.Contains(Callsite))
	{
		OutLevel = EBeamCacheHierarchyLevel::Callsite;
		return CallsiteCacheConfig.FindChecked(Callsite);
	}

	// Then, if we have no cache configuration for that specific callsite, we see if there are cache configurations for any requests coming from this calling context.
	if (CallingContext && CallingContextCacheConfig.Contains(CallingContext))
	{
		OutLevel = EBeamCacheHierarchyLevel::CallingContext;
		return CallingContextCacheConfig.FindChecked(CallingContext);
	}

	// Then, if we have no cache configuration for that specific calling context, we see if there is a cache configuration for this request type.
	if (RequestTypeCacheConfig.Contains(ReqType))
	{
		OutLevel = EBeamCacheHierarchyLevel::RequestType;
		return RequestTypeCacheConfig.FindChecked(ReqType);
	}

	// Finally, if no specific cache configuration has been defined, we return the global one. Which, by default, is disabled.
	OutLevel = EBeamCacheHierarchyLevel::Global;
	return CoreSettings->GlobalCacheConfiguration;
}

void UBeamResponseCache::SetCacheConfig(FRequestType ReqType, UObject* CallingContext, FBeamCacheConfig Config, TEnumAsByte<EBeamCacheHierarchyLevel>& OutLevel)
{
	// First, we prioritize this request type from this calling context.
	const auto Callsite = FBeamCachedRequestCallsite{ReqType, CallingContext};
	if (!ReqType.Name.IsEmpty() && CallingContext)
	{
		OutLevel = EBeamCacheHierarchyLevel::Callsite;
		CallsiteCacheConfig.Add(Callsite, Config);
		return;
	}

	// Then, if we have no cache configuration for that specific callsite, we see if there are cache configurations for any requests coming from this calling context.
	if (CallingContext)
	{
		OutLevel = EBeamCacheHierarchyLevel::CallingContext;
		CallingContextCacheConfig.Add(CallingContext, Config);
		return;
	}

	// Then, if we have no cache configuration for that specific calling context, we see if there is a cache configuration for this request type.
	if (!ReqType.Name.IsEmpty())
	{
		OutLevel = EBeamCacheHierarchyLevel::RequestType;
		RequestTypeCacheConfig.Add(ReqType, Config);
		return;
	}

	// Finally, if no specific cache configuration has been defined, we return the global one. Which, by default, is disabled.
	OutLevel = EBeamCacheHierarchyLevel::Global;
}
