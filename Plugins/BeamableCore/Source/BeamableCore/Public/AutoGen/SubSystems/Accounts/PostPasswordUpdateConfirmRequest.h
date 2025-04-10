
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PasswordUpdateConfirmation.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostPasswordUpdateConfirmRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPasswordUpdateConfirmRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPasswordUpdateConfirmation* Body = {};

	// Beam Base Request Declaration
	UPostPasswordUpdateConfirmRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PostPasswordUpdateConfirm",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Email,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPasswordUpdateConfirmRequest* Make(FString _Code, FString _NewPassword, FOptionalString _Email, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateConfirmSuccess, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateConfirmError, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPasswordUpdateConfirmComplete, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request);

using FPostPasswordUpdateConfirmFullResponse = FBeamFullResponse<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPasswordUpdateConfirmFullResponse, FPostPasswordUpdateConfirmFullResponse);
