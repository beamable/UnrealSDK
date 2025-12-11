
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectPaymentsGetPaymentsByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectPaymentsGetPaymentsByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectPaymentsGetPaymentsByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make ObjectPaymentsGetPaymentsByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectPaymentsGetPaymentsByObjectIdRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectPaymentsGetPaymentsByObjectIdSuccess, FBeamRequestContext, Context, UObjectPaymentsGetPaymentsByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectPaymentsGetPaymentsByObjectIdError, FBeamRequestContext, Context, UObjectPaymentsGetPaymentsByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectPaymentsGetPaymentsByObjectIdComplete, FBeamRequestContext, Context, UObjectPaymentsGetPaymentsByObjectIdRequest*, Request);

using FObjectPaymentsGetPaymentsByObjectIdFullResponse = FBeamFullResponse<UObjectPaymentsGetPaymentsByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectPaymentsGetPaymentsByObjectIdFullResponse, FObjectPaymentsGetPaymentsByObjectIdFullResponse);
