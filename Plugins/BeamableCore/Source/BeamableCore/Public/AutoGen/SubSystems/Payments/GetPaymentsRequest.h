
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CommonResponse.h"

#include "GetPaymentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPaymentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPaymentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetPaymentsRequest* MakeGetPaymentsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPaymentsSuccess, FBeamRequestContext, Context, UGetPaymentsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPaymentsError, FBeamRequestContext, Context, UGetPaymentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPaymentsComplete, FBeamRequestContext, Context, UGetPaymentsRequest*, Request);

using FGetPaymentsFullResponse = FBeamFullResponse<UGetPaymentsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPaymentsFullResponse, FGetPaymentsFullResponse);
