
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemResult.h"

#include "BeamFarmMsRegisterGroundItemRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsRegisterGroundItemRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URegisterGroundItemRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsRegisterGroundItemRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsRegisterGroundItem",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsRegisterGroundItemRequest* Make(FString _GroundItemId, FString _ContentId, int32 _Quantity, FString _ItemType, float _PosX, float _PosY, float _PosZ, FString _SpawnerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsRegisterGroundItemSuccess, FBeamRequestContext, Context, UBeamFarmMsRegisterGroundItemRequest*, Request, URegisterGroundItemResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsRegisterGroundItemError, FBeamRequestContext, Context, UBeamFarmMsRegisterGroundItemRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsRegisterGroundItemComplete, FBeamRequestContext, Context, UBeamFarmMsRegisterGroundItemRequest*, Request);

using FBeamFarmMsRegisterGroundItemFullResponse = FBeamFullResponse<UBeamFarmMsRegisterGroundItemRequest*, URegisterGroundItemResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsRegisterGroundItemFullResponse, FBeamFarmMsRegisterGroundItemFullResponse);
