
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#include "GetManifestExactRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestExactRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uid", Category="Beam")
	FString Uid = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestExactRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestExact",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestExactRequest* Make(FString _Uid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestExactSuccess, FBeamRequestContext, Context, UGetManifestExactRequest*, Request, UContentBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestExactError, FBeamRequestContext, Context, UGetManifestExactRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestExactComplete, FBeamRequestContext, Context, UGetManifestExactRequest*, Request);

using FGetManifestExactFullResponse = FBeamFullResponse<UGetManifestExactRequest*, UContentBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestExactFullResponse, FGetManifestExactFullResponse);
