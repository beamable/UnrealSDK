
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CreatePlanRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostPlansRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPlansRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreatePlanRequestBody* Body;

	// Beam Base Request Declaration
	UPostPlansRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_MessageBusAnalytics,_MessageBusCommon,Outer"))
	static UPostPlansRequest* MakePostPlansRequest(FString _Name, FOptionalArrayOfString _MessageBusAnalytics, FString _MemcachedHosts, bool _bMongoSSL, FString _PlatformJBDC, bool _bSharded, FString _MongoHosts, FOptionalArrayOfString _MessageBusCommon, TArray<URedisShardRequestBody*> _RedisShards, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlansSuccess, FBeamRequestContext, Context, UPostPlansRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlansError, FBeamRequestContext, Context, UPostPlansRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPlansComplete, FBeamRequestContext, Context, UPostPlansRequest*, Request);

using FPostPlansFullResponse = FBeamFullResponse<UPostPlansRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPlansFullResponse, FPostPlansFullResponse);
