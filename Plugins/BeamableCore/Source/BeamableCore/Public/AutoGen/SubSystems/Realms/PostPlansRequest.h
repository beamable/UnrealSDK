
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreatePlanRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostPlansRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPlansRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreatePlanRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostPlansRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostPlans",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_MongoSrvAddress,_MessageBusAnalytics,_MessageBusCommon,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPlansRequest* Make(bool _bMongoSSL, bool _bSharded, FString _Name, FString _MemcachedHosts, FString _PlatformJBDC, FString _MongoHosts, TArray<URedisShardRequestBody*> _RedisShards, FOptionalString _MongoSrvAddress, FOptionalArrayOfString _MessageBusAnalytics, FOptionalArrayOfString _MessageBusCommon, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlansSuccess, FBeamRequestContext, Context, UPostPlansRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlansError, FBeamRequestContext, Context, UPostPlansRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPlansComplete, FBeamRequestContext, Context, UPostPlansRequest*, Request);

using FPostPlansFullResponse = FBeamFullResponse<UPostPlansRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPlansFullResponse, FPostPlansFullResponse);
