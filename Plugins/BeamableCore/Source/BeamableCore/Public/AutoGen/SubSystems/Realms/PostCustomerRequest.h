
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/NewCustomerRequestBody.h"
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"

#include "PostCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UNewCustomerRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostCustomer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bHierarchy,_CustomerName,_Alias,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCustomerRequest* Make(FString _ProjectName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerSuccess, FBeamRequestContext, Context, UPostCustomerRequest*, Request, UNewCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomerError, FBeamRequestContext, Context, UPostCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCustomerComplete, FBeamRequestContext, Context, UPostCustomerRequest*, Request);

using FPostCustomerFullResponse = FBeamFullResponse<UPostCustomerRequest*, UNewCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCustomerFullResponse, FPostCustomerFullResponse);
