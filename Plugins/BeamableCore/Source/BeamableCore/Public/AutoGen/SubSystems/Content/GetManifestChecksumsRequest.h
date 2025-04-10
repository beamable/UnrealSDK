
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#include "GetManifestChecksumsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestChecksumsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestChecksumsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestChecksums",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestChecksumsRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestChecksumsSuccess, FBeamRequestContext, Context, UGetManifestChecksumsRequest*, Request, UManifestChecksums*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestChecksumsError, FBeamRequestContext, Context, UGetManifestChecksumsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestChecksumsComplete, FBeamRequestContext, Context, UGetManifestChecksumsRequest*, Request);

using FGetManifestChecksumsFullResponse = FBeamFullResponse<UGetManifestChecksumsRequest*, UManifestChecksums*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestChecksumsFullResponse, FGetManifestChecksumsFullResponse);
