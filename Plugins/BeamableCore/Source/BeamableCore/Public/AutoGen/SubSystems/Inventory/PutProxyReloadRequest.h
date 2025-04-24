
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutProxyReloadRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutProxyReloadRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamGamerTag ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutProxyReloadRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PutProxyReload",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutProxyReloadRequest* Make(FBeamGamerTag _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProxyReloadSuccess, FBeamRequestContext, Context, UPutProxyReloadRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutProxyReloadError, FBeamRequestContext, Context, UPutProxyReloadRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutProxyReloadComplete, FBeamRequestContext, Context, UPutProxyReloadRequest*, Request);

using FPutProxyReloadFullResponse = FBeamFullResponse<UPutProxyReloadRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutProxyReloadFullResponse, FPutProxyReloadFullResponse);
