
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UnarchiveProjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutProjectRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutProjectRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUnarchiveProjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutProjectRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PutProject",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutProjectRequest* Make(FBeamPid _ProjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectSuccess, FBeamRequestContext, Context, UPutProjectRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProjectError, FBeamRequestContext, Context, UPutProjectRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutProjectComplete, FBeamRequestContext, Context, UPutProjectRequest*, Request);

using FPutProjectFullResponse = FBeamFullResponse<UPutProjectRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutProjectFullResponse, FPutProjectFullResponse);
