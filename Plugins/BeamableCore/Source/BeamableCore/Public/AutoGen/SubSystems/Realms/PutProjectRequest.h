
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/UnarchiveProjectRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UUnarchiveProjectRequestBody* Body;

	// Beam Base Request Declaration
	UPutProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutProjectRequest* MakePutProjectRequest(FString _ProjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectSuccess, FBeamRequestContext, Context, UPutProjectRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectError, FBeamRequestContext, Context, UPutProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutProjectComplete, FBeamRequestContext, Context, UPutProjectRequest*, Request);

using FPutProjectFullResponse = FBeamFullResponse<UPutProjectRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutProjectFullResponse, FPutProjectFullResponse);
