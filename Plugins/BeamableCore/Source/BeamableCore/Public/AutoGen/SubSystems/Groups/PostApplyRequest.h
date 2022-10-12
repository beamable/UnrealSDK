
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupApplication.h"
#include "AutoGen/CommonResponse.h"

#include "PostApplyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostApplyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGroupApplication* Body;

	// Beam Base Request Declaration
	UPostApplyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_SubGroup,Outer"))
	static UPostApplyRequest* MakePostApplyRequest(int64 _ObjectId, FOptionalInt64 _SubGroup, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplySuccess, FBeamRequestContext, Context, UPostApplyRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplyError, FBeamRequestContext, Context, UPostApplyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostApplyComplete, FBeamRequestContext, Context, UPostApplyRequest*, Request);

using FPostApplyFullResponse = FBeamFullResponse<UPostApplyRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostApplyFullResponse, FPostApplyFullResponse);
