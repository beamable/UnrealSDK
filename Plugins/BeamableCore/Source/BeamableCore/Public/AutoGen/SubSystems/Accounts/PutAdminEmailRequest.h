
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EmailUpdateRequestBody.h"
#include "AutoGen/AccountsObjectAccount.h"

#include "PutAdminEmailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminEmailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UEmailUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPutAdminEmailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CodeType,Outer"))
	static UPutAdminEmailRequest* MakePutAdminEmailRequest(int64 _ObjectId, FString _NewEmail, FOptionalString _CodeType, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminEmailSuccess, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminEmailError, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminEmailComplete, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request);

using FPutAdminEmailFullResponse = FBeamFullResponse<UPutAdminEmailRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminEmailFullResponse, FPutAdminEmailFullResponse);
