
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ReplaceObjectsRequestBody.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#include "PostDataReplaceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataReplaceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UReplaceObjectsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostDataReplaceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PostDataReplace",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostDataReplaceRequest* Make(int64 _SourcePlayerId, int64 _TargetPlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataReplaceSuccess, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request, UCloudsavingBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataReplaceError, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataReplaceComplete, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request);

using FPostDataReplaceFullResponse = FBeamFullResponse<UPostDataReplaceRequest*, UCloudsavingBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnPostDataReplaceFullResponse, FPostDataReplaceFullResponse);
