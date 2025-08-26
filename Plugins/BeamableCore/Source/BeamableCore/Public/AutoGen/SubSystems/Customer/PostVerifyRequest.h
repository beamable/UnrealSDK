
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerRequestBody.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"

#include "PostVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCustomerActorNewCustomerRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PostVerify",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bHierarchy,_CustomerName,_Alias,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostVerifyRequest* Make(FString _RealmName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostVerifySuccess, FBeamRequestContext, Context, UPostVerifyRequest*, Request, UCustomerActorNewCustomerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostVerifyError, FBeamRequestContext, Context, UPostVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostVerifyComplete, FBeamRequestContext, Context, UPostVerifyRequest*, Request);

using FPostVerifyFullResponse = FBeamFullResponse<UPostVerifyRequest*, UCustomerActorNewCustomerResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostVerifyFullResponse, FPostVerifyFullResponse);
