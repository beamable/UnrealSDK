
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ContentOrText.h"

#include "BasicContentGetContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicContentGetContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FBeamContentId ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FString Version = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicContentGetContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BasicContentGetContent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicContentGetContentRequest* Make(FBeamContentId _ContentId, FString _Version, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentGetContentSuccess, FBeamRequestContext, Context, UBasicContentGetContentRequest*, Request, UContentOrText*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentGetContentError, FBeamRequestContext, Context, UBasicContentGetContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicContentGetContentComplete, FBeamRequestContext, Context, UBasicContentGetContentRequest*, Request);

using FBasicContentGetContentFullResponse = FBeamFullResponse<UBasicContentGetContentRequest*, UContentOrText*>;
DECLARE_DELEGATE_OneParam(FOnBasicContentGetContentFullResponse, FBasicContentGetContentFullResponse);
