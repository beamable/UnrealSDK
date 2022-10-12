
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MailResponse.h"

#include "BasicMailGetMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicMailGetMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mid")
	int64 Mid;

	// Body Params
	

	// Beam Base Request Declaration
	UBasicMailGetMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicMailGetMailRequest* MakeBasicMailGetMailRequest(int64 _Mid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailGetMailSuccess, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request, UMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailGetMailError, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicMailGetMailComplete, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request);

using FBasicMailGetMailFullResponse = FBeamFullResponse<UBasicMailGetMailRequest*, UMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicMailGetMailFullResponse, FBasicMailGetMailFullResponse);
