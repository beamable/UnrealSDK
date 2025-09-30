
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateServicePlanRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PostServicePlansRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServicePlansRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateServicePlanRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostServicePlansRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make PostServicePlans",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bMongoSharded,_bMongoTls,_MongoHosts,_MongoSrvAddress,_RedisShards,_MessageBusAnalytics,_MessageBusCommon,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostServicePlansRequest* Make(FString _Name, FOptionalBool _bMongoSharded, FOptionalBool _bMongoTls, FOptionalString _MongoHosts, FOptionalString _MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody _RedisShards, FOptionalArrayOfString _MessageBusAnalytics, FOptionalArrayOfString _MessageBusCommon, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicePlansSuccess, FBeamRequestContext, Context, UPostServicePlansRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicePlansError, FBeamRequestContext, Context, UPostServicePlansRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServicePlansComplete, FBeamRequestContext, Context, UPostServicePlansRequest*, Request);

using FPostServicePlansFullResponse = FBeamFullResponse<UPostServicePlansRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostServicePlansFullResponse, FPostServicePlansFullResponse);
