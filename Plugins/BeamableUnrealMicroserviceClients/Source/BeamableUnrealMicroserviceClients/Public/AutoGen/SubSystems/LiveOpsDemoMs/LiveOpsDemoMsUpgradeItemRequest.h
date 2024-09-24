
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsUpgradeItemResponse.h"

#include "LiveOpsDemoMsUpgradeItemRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsUpgradeItemRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpgradeItemRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMsUpgradeItemRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|LiveOpsDemoMs", DisplayName="Beam - Make LiveOpsDemoMsUpgradeItem",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMsUpgradeItemRequest* Make(int64 _UserID, int64 _ItemInstaceID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsUpgradeItemSuccess, FBeamRequestContext, Context, ULiveOpsDemoMsUpgradeItemRequest*, Request, ULiveOpsDemoMsUpgradeItemResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsUpgradeItemError, FBeamRequestContext, Context, ULiveOpsDemoMsUpgradeItemRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMsUpgradeItemComplete, FBeamRequestContext, Context, ULiveOpsDemoMsUpgradeItemRequest*, Request);

using FLiveOpsDemoMsUpgradeItemFullResponse = FBeamFullResponse<ULiveOpsDemoMsUpgradeItemRequest*, ULiveOpsDemoMsUpgradeItemResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMsUpgradeItemFullResponse, FLiveOpsDemoMsUpgradeItemFullResponse);
