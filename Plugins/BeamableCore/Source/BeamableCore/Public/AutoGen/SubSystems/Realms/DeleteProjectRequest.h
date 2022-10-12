
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ArchiveProjectRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UArchiveProjectRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteProjectRequest* MakeDeleteProjectRequest(FString _Pid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteProjectSuccess, FBeamRequestContext, Context, UDeleteProjectRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteProjectError, FBeamRequestContext, Context, UDeleteProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteProjectComplete, FBeamRequestContext, Context, UDeleteProjectRequest*, Request);

using FDeleteProjectFullResponse = FBeamFullResponse<UDeleteProjectRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteProjectFullResponse, FDeleteProjectFullResponse);