
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/EmailUpdateRequestBody.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"

#include "PutAdminEmailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminEmailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEmailUpdateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutAdminEmailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PutAdminEmail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_CodeType,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAdminEmailRequest* Make(FBeamAccountId _ObjectId, FString _NewEmail, FOptionalString _CodeType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminEmailSuccess, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request, UAccountsObjectAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminEmailError, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminEmailComplete, FBeamRequestContext, Context, UPutAdminEmailRequest*, Request);

using FPutAdminEmailFullResponse = FBeamFullResponse<UPutAdminEmailRequest*, UAccountsObjectAccount*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminEmailFullResponse, FPutAdminEmailFullResponse);
