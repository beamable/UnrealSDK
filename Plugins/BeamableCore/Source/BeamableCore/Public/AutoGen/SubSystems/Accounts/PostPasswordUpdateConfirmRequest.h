
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/PasswordUpdateConfirmation.h"
#include "AutoGen/EmptyResponse.h"

#include "PostPasswordUpdateConfirmRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPasswordUpdateConfirmRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPasswordUpdateConfirmation* Body;

	// Beam Base Request Declaration
	UPostPasswordUpdateConfirmRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Email,Outer"))
	static UPostPasswordUpdateConfirmRequest* MakePostPasswordUpdateConfirmRequest(FString _Code, FString _NewPassword, FOptionalString _Email, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateConfirmSuccess, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPasswordUpdateConfirmError, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPasswordUpdateConfirmComplete, FBeamRequestContext, Context, UPostPasswordUpdateConfirmRequest*, Request);

using FPostPasswordUpdateConfirmFullResponse = FBeamFullResponse<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPasswordUpdateConfirmFullResponse, FPostPasswordUpdateConfirmFullResponse);
