#pragma once

#include "BeamBackendDataCache.h"
#include "BeamCacheConfig.h"
#include "BeamCoreSettings.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/BeamBaseRequestInterface.h"

#include "BeamResponseCache.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamResponseCache : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @brief Settings so that we can fall back to the global cache config.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	const UBeamCoreSettings* CoreSettings;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FRequestType, FBeamCacheConfig> RequestTypeCacheConfig;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<UObject*, FBeamCacheConfig> CallingContextCacheConfig;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FBeamCachedRequestCallsite, FBeamCacheConfig> CallsiteCacheConfig;

	FBeamBackendDataCache<FString> ResponseStringCache;
	FBeamBackendDataCache<FDateTime> CacheHitTimestamps;


	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamResponseCache* GetSelf() { return GEngine->GetEngineSubsystem<UBeamResponseCache>(); }

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/**
	 * @brief Given an outgoing request, tries to hit the response cache for it. If it finds it, returns true and @ref OutResponse contains the cached response string.  
	 *
	 * @param ReqDataObject The Request Object of the request being made.
	 * @param ReqObject The built Unreal request object of the request being made.
	 * @param CallingContext The calling context of the request being made.	 
	 * @param OutResponse The serialized response content as it was returned.
	 * 
	 * @return True/False based on whether the cached value should be used. OutResponse is an empty string in case of FALSE and the last cached serialized response string in case of TRUE. 
	 */
	bool TryHitResponseCache(const TScriptInterface<IBeamBaseRequestInterface> ReqDataObject, const TUnrealRequestPtr ReqObject, const UObject* CallingContext, FString& OutResponse);

	/**
	 * @brief Given a response string and information about the request that produced it, caches its value in the correct hierarchical cache. 
	 * 
	 * @param ReqType The type of the request being made.
	 * @param CallingContext The calling context of the request being made.
	 * @param ReqObject The built Unreal request object of the request being made.
	 * @param ResponseAsString The serialized response string.
	 */
	void UpdateResponseCache(FRequestType ReqType, const UObject* CallingContext, const TUnrealRequestPtr ReqObject, FString ResponseAsString);

	/**
	 * @brief Invalidates all caches.
	 */
	void InvalidateAll();

	/**
	 * @brief Clears all non-global cache configurations and invalidates their caches. 
	 */
	void ClearNonGlobalConfigs();

	/**
	 * @brief Sets the Cache Config at a certain hierarchy level.
	 * 
	 * @param ReqType The type of the request. 
	 * @param CallingContext A UObject representing the context from which this request is made. Used to support multiple PIE.
	 * @param Config The cache config that will be used to control the cache at this hierarchy level.
	 * @param OutLevel The level that the config was placed in (mostly here for debugging purposes).
	 *                 Global if ReqType.IsEmpty and CallingContext is null.
	 *                 RequestType if ReqType is not empty and CallingContext is null.
	 *                 CallingContext if ReqType is empty and CallingContext is not null.
	 *                 Callsite if ReqType is not Empty and CallingContext is not null.
	 */
	UFUNCTION(BlueprintCallable)
	void SetCacheConfig(FRequestType ReqType, UObject* CallingContext, FBeamCacheConfig Config, TEnumAsByte<EBeamCacheHierarchyLevel>& OutLevel);

private:
	/**
	 * @brief Gets the cache config for the given request type and calling context. Does this hierarchically.
	 * First looks at any cache configuration set up for a specific callsite.
	 * Then, looks at any cache configuration set up for the calling context.
	 * Then, looks at any cache configuration set up for the request type.
	 * If none are found, return the GlobalCacheConfig (configurable in the Project Settings > Engine > BeamCore)
	 * 
	 * @param ReqType The type of the request being made (each Request object has a function that returns this). 
	 * @param CallingContext An UObject that defines a context for this request.
	 * @param OutLevel The Hierarchy Level currently active for the given RequestType and Calling Context.
	 * 
	 * @return The cache configuration that is currently valid for that request. 
	 */
	FBeamCacheConfig FindCacheConfig(FRequestType ReqType, const UObject* CallingContext, TEnumAsByte<EBeamCacheHierarchyLevel>& OutLevel) const;


	/**
	 * @brief Determines whether or not the current response cache should be invalidated based on the current active configuration for it.
	 *
	 * @param ReqObject The Request Object of the request being made.
	 * @param ReqType The type of the request being made.
	 * @param CallingContext The calling context of the request being made.
	 * @param ReqHeader The authentication header for the request being made.
	 * @param ReqRoute The URL of the request being made.
	 * @param ReqBody The serialized body of the request being made.
	 * 
	 * @return TRUE, if we should invalidate the cache. FALSE, otherwise. 
	 */
	UFUNCTION(Category="Beam")
	bool ShouldInvalidateResponseCache(const TScriptInterface<IBeamBaseRequestInterface> ReqObject, FRequestType ReqType, const UObject* CallingContext, FString ReqHeader, FString ReqRoute,
	                                   FString ReqBody) const;


	/**
	 * @brief Helper function that gets from a FBeamBackendDataCache based on the given Hierarchy level. 
	 */
	template <typename T>
	static bool TryGetFromCacheHierarchy(const TEnumAsByte<EBeamCacheHierarchyLevel> Level, const FBeamBackendDataCache<T>& Cache, FRequestType ReqType, const UObject* CallingContext,
	                                     FString ReqHeader,
	                                     FString ReqRoute, FString ReqBody, T& CacheVal)
	{
		switch (Level)
		{
		case Global:
			{
				const auto Key = FGlobalCacheKey{ReqHeader, ReqRoute, ReqBody};
				const auto bContains = Cache.GlobalCache.Contains(Key);
				CacheVal = bContains ? Cache.GlobalCache.FindChecked(Key) : T{};
				return bContains;
			}
		case RequestType:
			{
				const auto Key = FRequestTypeCacheKey{ReqType, ReqHeader, ReqRoute, ReqBody};
				const auto bContains = Cache.RequestTypeCache.Contains(Key);
				CacheVal = bContains ? Cache.RequestTypeCache.FindChecked(Key) : T{};
				return bContains;
			}
		case EBeamCacheHierarchyLevel::CallingContext:
			{
				if (CallingContext)
				{
					const auto Key = FCallingContextCacheKey{CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					const auto bContains = Cache.CallingContextCache.Contains(Key);
					CacheVal = bContains ? Cache.CallingContextCache.FindChecked(Key) : T{};
					return bContains;
				}
				CacheVal = T{};
				return false;
			}
		case Callsite:
			{
				if (CallingContext)
				{
					const auto Key = FCallsiteCacheKey{ReqType, CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					const auto bContains = Cache.CallsiteCache.Contains(Key);
					CacheVal = bContains ? Cache.CallsiteCache.FindChecked(Key) : T{};
					return bContains;
				}
				CacheVal = T{};
				return false;
			}
		default: ;
		}

		CacheVal = T{};
		return false;
	}


	/**
	 * @brief Helper function that updates a FBeamBackendDataCache based on the given Hierarchy level and data. 
	 */
	template <typename T>
	static void UpdateCacheAtHierarchyLevel(const TEnumAsByte<EBeamCacheHierarchyLevel> Level, FBeamBackendDataCache<T>& Cache, const T& CacheVal, FRequestType ReqType, const UObject* CallingContext,
	                                        FString ReqHeader, FString ReqRoute, FString ReqBody)
	{
		switch (Level)
		{
		case Global:
			{
				const auto Key = FGlobalCacheKey{ReqHeader, ReqRoute, ReqBody};
				if (Cache.GlobalCache.Contains(Key))
					Cache.GlobalCache[Key] = CacheVal;
				else
					Cache.GlobalCache.Add(Key, CacheVal);

				break;
			}
		case RequestType:
			{
				const auto Key = FRequestTypeCacheKey{ReqType, ReqHeader, ReqRoute, ReqBody};
				if (Cache.RequestTypeCache.Contains(Key))
					Cache.RequestTypeCache[Key] = CacheVal;
				else
					Cache.RequestTypeCache.Add(Key, CacheVal);

				break;
			}
		case EBeamCacheHierarchyLevel::CallingContext:
			{
				if (CallingContext)
				{
					const auto Key = FCallingContextCacheKey{CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					if (Cache.CallingContextCache.Contains(Key))
						Cache.CallingContextCache[Key] = CacheVal;
					else
						Cache.CallingContextCache.Add(Key, CacheVal);
				}
				break;
			}
		case Callsite:
			{
				if (CallingContext)
				{
					const auto Key = FCallsiteCacheKey{ReqType, CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					if (Cache.CallsiteCache.Contains(Key))
						Cache.CallsiteCache[Key] = CacheVal;
					else
						Cache.CallsiteCache.Add(Key, CacheVal);
				}
				break;
			}
		default: ;
		}
	}

	/**
	 * @brief Helper function that invalidates the data in a FBeamBackendDataCache based on the given Hierarchy level. 
	 */
	template <typename T>
	static void InvalidateCacheAtHierarchyLevel(const TEnumAsByte<EBeamCacheHierarchyLevel> Level, FBeamBackendDataCache<T>& Cache, FRequestType ReqType, const UObject* CallingContext,
	                                            FString ReqHeader,
	                                            FString ReqRoute, FString ReqBody)
	{
		switch (Level)
		{
		case Global:
			{
				const auto Key = FGlobalCacheKey{ReqHeader, ReqRoute, ReqBody};
				if (Cache.GlobalCache.Contains(Key)) Cache.GlobalCache.Remove(Key);
				break;
			}
		case RequestType:
			{
				const auto Key = FRequestTypeCacheKey{ReqType, ReqHeader, ReqRoute, ReqBody};
				if (Cache.RequestTypeCache.Contains(Key)) Cache.RequestTypeCache.Remove(Key);
				break;
			}
		case EBeamCacheHierarchyLevel::CallingContext:
			{
				if (CallingContext)
				{
					const auto Key = FCallingContextCacheKey{CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					if (Cache.CallingContextCache.Contains(Key)) Cache.CallingContextCache.Remove(Key);
				}
				break;
			}
		case Callsite:
			{
				if (CallingContext)
				{
					const auto Key = FCallsiteCacheKey{ReqType, CallingContext->GetName(), ReqHeader, ReqRoute, ReqBody};
					if (Cache.CallsiteCache.Contains(Key)) Cache.CallsiteCache.Remove(Key);
				}
				break;
			}
		default: ;
		}
	}
};
