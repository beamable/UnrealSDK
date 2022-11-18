
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/AccountsObjectAccount.h"

#include "DeleteAdminForgetRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAdminForgetRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteAdminForgetRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make DeleteAdminForget",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UDeleteAdminForgetRequest* Make(int64 _ObjectId, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminForgetSuccess, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminForgetError, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAdminForgetComplete, FBeamRequestContext, Context, UDeleteAdminForgetRequest*, Request);

using FDeleteAdminForgetFullResponse = FBeamFullResponse<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAdminForgetFullResponse, FDeleteAdminForgetFullResponse);
