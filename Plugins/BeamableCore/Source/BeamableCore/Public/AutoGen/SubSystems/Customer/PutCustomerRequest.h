
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdateCustomerRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutCustomerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutCustomerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateCustomerRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutCustomerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutCustomer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PaymentStatus,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutCustomerRequest* Make(FString _CustomerId, FOptionalPaymentStatus _PaymentStatus, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutCustomerSuccess, FBeamRequestContext, Context, UPutCustomerRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutCustomerError, FBeamRequestContext, Context, UPutCustomerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutCustomerComplete, FBeamRequestContext, Context, UPutCustomerRequest*, Request);

using FPutCustomerFullResponse = FBeamFullResponse<UPutCustomerRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutCustomerFullResponse, FPutCustomerFullResponse);
