
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/EmailUpdateRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostEmailUpdateInitRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostEmailUpdateInitRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UEmailUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostEmailUpdateInitRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CodeType,Outer"))
	static UPostEmailUpdateInitRequest* MakePostEmailUpdateInitRequest(FString _NewEmail, FOptionalString _CodeType, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostEmailUpdateInitSuccess, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostEmailUpdateInitError, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostEmailUpdateInitComplete, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request);

using FPostEmailUpdateInitFullResponse = FBeamFullResponse<UPostEmailUpdateInitRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostEmailUpdateInitFullResponse, FPostEmailUpdateInitFullResponse);
