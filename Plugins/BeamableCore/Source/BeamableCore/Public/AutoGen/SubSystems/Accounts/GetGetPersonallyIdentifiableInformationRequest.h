
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AccountPersonallyIdentifiableInformationResponse.h"

#include "GetGetPersonallyIdentifiableInformationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGetPersonallyIdentifiableInformationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FString Query = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetGetPersonallyIdentifiableInformationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetGetPersonallyIdentifiableInformation",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetGetPersonallyIdentifiableInformationRequest* Make(FString _Query, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGetPersonallyIdentifiableInformationSuccess, FBeamRequestContext, Context, UGetGetPersonallyIdentifiableInformationRequest*, Request, UAccountPersonallyIdentifiableInformationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGetPersonallyIdentifiableInformationError, FBeamRequestContext, Context, UGetGetPersonallyIdentifiableInformationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGetPersonallyIdentifiableInformationComplete, FBeamRequestContext, Context, UGetGetPersonallyIdentifiableInformationRequest*, Request);

using FGetGetPersonallyIdentifiableInformationFullResponse = FBeamFullResponse<UGetGetPersonallyIdentifiableInformationRequest*, UAccountPersonallyIdentifiableInformationResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetGetPersonallyIdentifiableInformationFullResponse, FGetGetPersonallyIdentifiableInformationFullResponse);
