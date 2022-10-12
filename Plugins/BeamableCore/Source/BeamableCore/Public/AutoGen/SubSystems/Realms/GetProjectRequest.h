
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ProjectView.h"

#include "GetProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetProjectRequest* MakeGetProjectRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetProjectSuccess, FBeamRequestContext, Context, UGetProjectRequest*, Request, UProjectView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetProjectError, FBeamRequestContext, Context, UGetProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetProjectComplete, FBeamRequestContext, Context, UGetProjectRequest*, Request);

using FGetProjectFullResponse = FBeamFullResponse<UGetProjectRequest*, UProjectView*>;
DECLARE_DELEGATE_OneParam(FOnGetProjectFullResponse, FGetProjectFullResponse);
