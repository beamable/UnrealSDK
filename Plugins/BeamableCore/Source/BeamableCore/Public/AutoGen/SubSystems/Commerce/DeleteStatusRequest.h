
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/ClearStatusRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UClearStatusRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteStatusRequest* MakeDeleteStatusRequest(int64 _ObjectId, FString _Store, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatusSuccess, FBeamRequestContext, Context, UDeleteStatusRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatusError, FBeamRequestContext, Context, UDeleteStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteStatusComplete, FBeamRequestContext, Context, UDeleteStatusRequest*, Request);

using FDeleteStatusFullResponse = FBeamFullResponse<UDeleteStatusRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteStatusFullResponse, FDeleteStatusFullResponse);
