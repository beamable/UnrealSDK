
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Query.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#include "PostQueryLogsResultRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostQueryLogsResultRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UQuery* Body = {};

	// Beam Base Request Declaration
	UPostQueryLogsResultRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostQueryLogsResult",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostQueryLogsResultRequest* Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQueryLogsResultSuccess, FBeamRequestContext, Context, UPostQueryLogsResultRequest*, Request, UGetSignedUrlResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQueryLogsResultError, FBeamRequestContext, Context, UPostQueryLogsResultRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostQueryLogsResultComplete, FBeamRequestContext, Context, UPostQueryLogsResultRequest*, Request);

using FPostQueryLogsResultFullResponse = FBeamFullResponse<UPostQueryLogsResultRequest*, UGetSignedUrlResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostQueryLogsResultFullResponse, FPostQueryLogsResultFullResponse);
