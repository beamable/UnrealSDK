
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BatchDeleteInFlightRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "DeleteInflightFailuresRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteInflightFailuresRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBatchDeleteInFlightRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteInflightFailuresRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make DeleteInflightFailures",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteInflightFailuresRequest* Make(TArray<FString> _InFlightFailureIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteInflightFailuresSuccess, FBeamRequestContext, Context, UDeleteInflightFailuresRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteInflightFailuresError, FBeamRequestContext, Context, UDeleteInflightFailuresRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteInflightFailuresComplete, FBeamRequestContext, Context, UDeleteInflightFailuresRequest*, Request);

using FDeleteInflightFailuresFullResponse = FBeamFullResponse<UDeleteInflightFailuresRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnDeleteInflightFailuresFullResponse, FDeleteInflightFailuresFullResponse);
