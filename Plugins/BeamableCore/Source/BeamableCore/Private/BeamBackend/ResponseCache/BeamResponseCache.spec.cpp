#include "BeamBackend/ResponseCache/BeamResponseCache.spec.h"
#include "BeamBackend/BeamBackendTestCallbacks.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"


void FBeamResponseCacheSpec::Define()
{
	Describe("Cache Hits", [this]()
	{
		const FBeamRealmHandle FakeRealmHandle{FString("000000000000"), FString("DE_000000000000")};
		const FBeamRetryConfig FakeNoRetryConfig{{}, {}, 10, TArray<float>{0.5, 1}, 0};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			BeamResponseCache = GEngine->GetEngineSubsystem<UBeamResponseCache>();
			BeamResponseCache->InvalidateAll();
			BeamResponseCache->ClearNonGlobalConfigs();
		});

		It("should not hit cache if cache was never updated.", [=, this]()
		{
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();

			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeGetRequest);

			FString CachedResp;
			const auto HitCache = BeamResponseCache->TryHitResponseCache(FakeGetRequest, Request, nullptr, CachedResp);

			TestFalse("Request was not cached", HitCache);

			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
		});

		It("should update and then retrieve the cache for this request type.", [=, this]()
		{
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();

			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeGetRequest);

			// Set up a cache config for this request type.
			BeamResponseCache->RequestTypeCacheConfig.Add(FakeGetRequest->GetRequestType(), FBeamCacheConfig{Time, 600});
			BeamResponseCache->UpdateResponseCache(FakeGetRequest->GetRequestType(), nullptr, Request, TEXT("Fake Response"));

			FString CachedResp;
			const auto HitCache = BeamResponseCache->TryHitResponseCache(FakeGetRequest, Request, nullptr, CachedResp);

			TestTrue("Did hit cache", HitCache);
			TestEqual("Cached Response with latest received response", CachedResp, TEXT("Fake Response"));

			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
		});

		It("should update the cache for this request type, but fail to retrieve it when hitting a different layer of the hierarchy.", [=, this]()
		{
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();

			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeGetRequest);

			// Set up a cache config for this request type.
			TEnumAsByte<EBeamCacheHierarchyLevel> SetAtLevel;
			BeamResponseCache->SetCacheConfig(FakeGetRequest->GetRequestType(), nullptr, FBeamCacheConfig{Time, 600}, SetAtLevel);
			TestEqual("Set config at correct level -- ReqType", SetAtLevel, EBeamCacheHierarchyLevel::RequestType);

			// Set up a cache config with a specific calling context.
			BeamResponseCache->SetCacheConfig(FString{}, FakeGetRequest, FBeamCacheConfig{Time, 600}, SetAtLevel);
			TestEqual("Set config at correct level -- CallingContext", SetAtLevel, EBeamCacheHierarchyLevel::CallingContext);

			// Updates the cache at the RequestType cache-level but Not at the calling context level. 
			BeamResponseCache->UpdateResponseCache(FakeGetRequest->GetRequestType(), nullptr, Request, TEXT("Fake Response"));

			// Try to get the cache at the calling context cache-level. We should not hit the cache here.
			FString CachedResp;
			const auto HitCallingContextCache = BeamResponseCache->TryHitResponseCache(FakeGetRequest, Request, FakeGetRequest, CachedResp);

			// Asserts that is the case.
			TestFalse("Did not hit cache", HitCallingContextCache);

			// Then we Updates the cache at the CallingContext cache-level. 
			BeamResponseCache->UpdateResponseCache(FakeGetRequest->GetRequestType(), FakeGetRequest, Request, TEXT("Fake Response"));
			const auto NowHitCallingContextCache = BeamResponseCache->TryHitResponseCache(FakeGetRequest, Request, FakeGetRequest, CachedResp);

			// Verify that we now hit the cache correctly
			TestTrue("Did hit cache", NowHitCallingContextCache);
			TestEqual("Cached Response with latest received response", CachedResp, TEXT("Fake Response"));

			// Set up a cache config with a specific calling context.
			BeamResponseCache->SetCacheConfig(FakeGetRequest->GetRequestType(), FakeGetRequest, FBeamCacheConfig{Time, 600}, SetAtLevel);			
			TestEqual("Set config at correct level -- Callsite", SetAtLevel, EBeamCacheHierarchyLevel::Callsite);

			// Then we Updates the cache at the CallingContext cache-level. 
			BeamResponseCache->UpdateResponseCache(FakeGetRequest->GetRequestType(), FakeGetRequest, Request, TEXT("Fake Response"));
			const auto NowHitCallsiteCache = BeamResponseCache->TryHitResponseCache(FakeGetRequest, Request, FakeGetRequest, CachedResp);

			// Verify that we now hit the cache correctly
			TestTrue("Did hit cache", NowHitCallsiteCache);
			TestEqual("Cached Response with latest received response", CachedResp, TEXT("Fake Response"));
			
			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
		});
	});
}
