
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetPlayerLevelResult.h"

#include "BeamFarmMsGetPlayerLevelRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsGetPlayerLevelRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamFarmMsGetPlayerLevelRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsGetPlayerLevel",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsGetPlayerLevelRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetPlayerLevelSuccess, FBeamRequestContext, Context, UBeamFarmMsGetPlayerLevelRequest*, Request, UGetPlayerLevelResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetPlayerLevelError, FBeamRequestContext, Context, UBeamFarmMsGetPlayerLevelRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsGetPlayerLevelComplete, FBeamRequestContext, Context, UBeamFarmMsGetPlayerLevelRequest*, Request);

using FBeamFarmMsGetPlayerLevelFullResponse = FBeamFullResponse<UBeamFarmMsGetPlayerLevelRequest*, UGetPlayerLevelResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsGetPlayerLevelFullResponse, FBeamFarmMsGetPlayerLevelFullResponse);
