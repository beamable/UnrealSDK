
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CreateProjectRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostProjectBeamableRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectBeamableRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreateProjectRequestBody* Body;

	// Beam Base Request Declaration
	UPostProjectBeamableRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Plan,_bSharded,_Parent,Outer"))
	static UPostProjectBeamableRequest* MakePostProjectBeamableRequest(FString _Name, FOptionalString _Plan, FOptionalBool _bSharded, FOptionalString _Parent, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectBeamableSuccess, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectBeamableError, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectBeamableComplete, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request);

using FPostProjectBeamableFullResponse = FBeamFullResponse<UPostProjectBeamableRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectBeamableFullResponse, FPostProjectBeamableFullResponse);
