
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NewCustomerRequestBody.h"
#include "AutoGen/NewCustomerResponse.h"

#include "PostCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNewCustomerRequestBody* Body;

	// Beam Base Request Declaration
	UPostCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CustomerName,_bHierarchy,_Alias,Outer"))
	static UPostCustomerRequest* MakePostCustomerRequest(FString _ProjectName, FString _Email, FOptionalString _CustomerName, FOptionalBool _bHierarchy, FOptionalString _Alias, FString _Password, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerSuccess, FBeamRequestContext, Context, UPostCustomerRequest*, Request, UNewCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerError, FBeamRequestContext, Context, UPostCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCustomerComplete, FBeamRequestContext, Context, UPostCustomerRequest*, Request);

using FPostCustomerFullResponse = FBeamFullResponse<UPostCustomerRequest*, UNewCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCustomerFullResponse, FPostCustomerFullResponse);
