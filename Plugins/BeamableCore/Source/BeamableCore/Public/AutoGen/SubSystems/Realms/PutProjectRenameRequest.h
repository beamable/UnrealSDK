
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RenameProjectRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutProjectRenameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutProjectRenameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URenameProjectRequestBody* Body;

	// Beam Base Request Declaration
	UPutProjectRenameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutProjectRenameRequest* MakePutProjectRenameRequest(FString _ProjectId, FString _NewName, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectRenameSuccess, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectRenameError, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutProjectRenameComplete, FBeamRequestContext, Context, UPutProjectRenameRequest*, Request);

using FPutProjectRenameFullResponse = FBeamFullResponse<UPutProjectRenameRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutProjectRenameFullResponse, FPutProjectRenameFullResponse);
