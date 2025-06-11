
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/NewCustomerRequestBody.h"
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"

#include "PostCustomerVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCustomerVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UNewCustomerRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCustomerVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostCustomerVerify",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bHierarchy,_CustomerName,_Alias,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCustomerVerifyRequest* Make(FString _ProjectName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerVerifySuccess, FBeamRequestContext, Context, UPostCustomerVerifyRequest*, Request, UNewCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerVerifyError, FBeamRequestContext, Context, UPostCustomerVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCustomerVerifyComplete, FBeamRequestContext, Context, UPostCustomerVerifyRequest*, Request);

using FPostCustomerVerifyFullResponse = FBeamFullResponse<UPostCustomerVerifyRequest*, UNewCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCustomerVerifyFullResponse, FPostCustomerVerifyFullResponse);
