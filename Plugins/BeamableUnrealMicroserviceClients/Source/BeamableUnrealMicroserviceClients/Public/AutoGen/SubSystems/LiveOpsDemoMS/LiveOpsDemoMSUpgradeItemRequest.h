
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSUpgradeItemResponse.h"

#include "LiveOpsDemoMSUpgradeItemRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSUpgradeItemRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpgradeItemRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMSUpgradeItemRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSUpgradeItem",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMSUpgradeItemRequest* Make(int64 _GamerTag, int64 _ItemInstaceID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSUpgradeItemSuccess, FBeamRequestContext, Context, ULiveOpsDemoMSUpgradeItemRequest*, Request, ULiveOpsDemoMSUpgradeItemResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSUpgradeItemError, FBeamRequestContext, Context, ULiveOpsDemoMSUpgradeItemRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMSUpgradeItemComplete, FBeamRequestContext, Context, ULiveOpsDemoMSUpgradeItemRequest*, Request);

using FLiveOpsDemoMSUpgradeItemFullResponse = FBeamFullResponse<ULiveOpsDemoMSUpgradeItemRequest*, ULiveOpsDemoMSUpgradeItemResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMSUpgradeItemFullResponse, FLiveOpsDemoMSUpgradeItemFullResponse);
