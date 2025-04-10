
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Query.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteQueryLogsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteQueryLogsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UQuery* Body = {};

	// Beam Base Request Declaration
	UDeleteQueryLogsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteQueryLogs",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteQueryLogsRequest* Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteQueryLogsSuccess, FBeamRequestContext, Context, UDeleteQueryLogsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteQueryLogsError, FBeamRequestContext, Context, UDeleteQueryLogsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteQueryLogsComplete, FBeamRequestContext, Context, UDeleteQueryLogsRequest*, Request);

using FDeleteQueryLogsFullResponse = FBeamFullResponse<UDeleteQueryLogsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteQueryLogsFullResponse, FDeleteQueryLogsFullResponse);
