
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountsObjectAccount.h"

#include "DeleteAdminForgetRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAdminForgetRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteAdminForgetRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteAdminForgetRequest* MakeDeleteAdminForgetRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminForgetSuccess, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminForgetError, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAdminForgetComplete, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request);

using FDeleteAdminForgetFullResponse = FBeamFullResponse<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAdminForgetFullResponse, FDeleteAdminForgetFullResponse);
