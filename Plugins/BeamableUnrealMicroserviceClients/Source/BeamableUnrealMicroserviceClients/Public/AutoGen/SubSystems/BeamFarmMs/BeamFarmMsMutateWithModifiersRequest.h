
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersResult.h"

#include "BeamFarmMsMutateWithModifiersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsMutateWithModifiersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMutateWithModifiersRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsMutateWithModifiersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsMutateWithModifiers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsMutateWithModifiersRequest* Make(FString _PlantItemContentId, int64 _PlantItemInstanceId, TArray<FString> _ModifierContentIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsMutateWithModifiersSuccess, FBeamRequestContext, Context, UBeamFarmMsMutateWithModifiersRequest*, Request, UMutateWithModifiersResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsMutateWithModifiersError, FBeamRequestContext, Context, UBeamFarmMsMutateWithModifiersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsMutateWithModifiersComplete, FBeamRequestContext, Context, UBeamFarmMsMutateWithModifiersRequest*, Request);

using FBeamFarmMsMutateWithModifiersFullResponse = FBeamFullResponse<UBeamFarmMsMutateWithModifiersRequest*, UMutateWithModifiersResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsMutateWithModifiersFullResponse, FBeamFarmMsMutateWithModifiersFullResponse);
