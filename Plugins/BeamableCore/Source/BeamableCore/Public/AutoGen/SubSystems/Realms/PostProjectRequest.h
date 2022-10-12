
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CreateProjectRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreateProjectRequestBody* Body;

	// Beam Base Request Declaration
	UPostProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Plan,_bSharded,_Parent,Outer"))
	static UPostProjectRequest* MakePostProjectRequest(FString _Name, FOptionalString _Plan, FOptionalBool _bSharded, FOptionalString _Parent, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectSuccess, FBeamRequestContext, Context, UPostProjectRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectError, FBeamRequestContext, Context, UPostProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectComplete, FBeamRequestContext, Context, UPostProjectRequest*, Request);

using FPostProjectFullResponse = FBeamFullResponse<UPostProjectRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectFullResponse, FPostProjectFullResponse);
