
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerRequestBody.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"

#include "PostCustomersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCustomersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCustomerActorNewCustomerRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCustomersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PostCustomers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bHierarchy,_CustomerName,_Alias,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCustomersRequest* Make(FString _RealmName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomersSuccess, FBeamRequestContext, Context, UPostCustomersRequest*, Request, UCustomerActorNewCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomersError, FBeamRequestContext, Context, UPostCustomersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCustomersComplete, FBeamRequestContext, Context, UPostCustomersRequest*, Request);

using FPostCustomersFullResponse = FBeamFullResponse<UPostCustomersRequest*, UCustomerActorNewCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCustomersFullResponse, FPostCustomersFullResponse);
