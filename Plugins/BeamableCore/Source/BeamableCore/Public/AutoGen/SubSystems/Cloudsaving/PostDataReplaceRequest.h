
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ReplaceObjectsRequestBody.h"
#include "AutoGen/Manifest.h"

#include "PostDataReplaceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataReplaceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UReplaceObjectsRequestBody* Body;

	// Beam Base Request Declaration
	UPostDataReplaceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostDataReplaceRequest* MakePostDataReplaceRequest(int64 _SourcePlayerId, int64 _TargetPlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataReplaceSuccess, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request, UManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataReplaceError, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataReplaceComplete, FBeamRequestContext, Context, UPostDataReplaceRequest*, Request);

using FPostDataReplaceFullResponse = FBeamFullResponse<UPostDataReplaceRequest*, UManifest*>;
DECLARE_DELEGATE_OneParam(FOnPostDataReplaceFullResponse, FPostDataReplaceFullResponse);
