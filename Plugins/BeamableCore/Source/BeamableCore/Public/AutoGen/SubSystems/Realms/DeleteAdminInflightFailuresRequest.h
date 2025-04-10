
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BatchDeleteInFlightRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteAdminInflightFailuresRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAdminInflightFailuresRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBatchDeleteInFlightRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteAdminInflightFailuresRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make DeleteAdminInflightFailures",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteAdminInflightFailuresRequest* Make(TArray<FString> _InFlightFailureIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminInflightFailuresSuccess, FBeamRequestContext, Context, UDeleteAdminInflightFailuresRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminInflightFailuresError, FBeamRequestContext, Context, UDeleteAdminInflightFailuresRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAdminInflightFailuresComplete, FBeamRequestContext, Context, UDeleteAdminInflightFailuresRequest*, Request);

using FDeleteAdminInflightFailuresFullResponse = FBeamFullResponse<UDeleteAdminInflightFailuresRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAdminInflightFailuresFullResponse, FDeleteAdminInflightFailuresFullResponse);
