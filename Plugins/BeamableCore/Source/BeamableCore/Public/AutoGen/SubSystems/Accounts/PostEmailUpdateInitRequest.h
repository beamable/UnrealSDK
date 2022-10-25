
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEmailUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostEmailUpdateInitRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make PostEmailUpdateInit",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_CodeType,Outer"))
	static UPostEmailUpdateInitRequest* Make(FString _NewEmail, FOptionalString _CodeType, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostEmailUpdateInitSuccess, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostEmailUpdateInitError, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostEmailUpdateInitComplete, FBeamRequestContext, Context, UPostEmailUpdateInitRequest*, Request);

using FPostEmailUpdateInitFullResponse = FBeamFullResponse<UPostEmailUpdateInitRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostEmailUpdateInitFullResponse, FPostEmailUpdateInitFullResponse);
