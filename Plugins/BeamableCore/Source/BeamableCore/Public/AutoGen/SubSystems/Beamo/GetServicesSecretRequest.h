
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2GetServiceSecretResponse.h"

#include "GetServicesSecretRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetServicesSecretRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetServicesSecretRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetServicesSecret",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetServicesSecretRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicesSecretSuccess, FBeamRequestContext, Context, UGetServicesSecretRequest*, Request, UBeamoV2GetServiceSecretResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicesSecretError, FBeamRequestContext, Context, UGetServicesSecretRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetServicesSecretComplete, FBeamRequestContext, Context, UGetServicesSecretRequest*, Request);

using FGetServicesSecretFullResponse = FBeamFullResponse<UGetServicesSecretRequest*, UBeamoV2GetServiceSecretResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetServicesSecretFullResponse, FGetServicesSecretFullResponse);
