
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"

#include "GetOtelAuthReaderConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOtelAuthReaderConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetOtelAuthReaderConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make GetOtelAuthReaderConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetOtelAuthReaderConfigRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelAuthReaderConfigSuccess, FBeamRequestContext, Context, UGetOtelAuthReaderConfigRequest*, Request, UOtelAuthConfig*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelAuthReaderConfigError, FBeamRequestContext, Context, UGetOtelAuthReaderConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetOtelAuthReaderConfigComplete, FBeamRequestContext, Context, UGetOtelAuthReaderConfigRequest*, Request);

using FGetOtelAuthReaderConfigFullResponse = FBeamFullResponse<UGetOtelAuthReaderConfigRequest*, UOtelAuthConfig*>;
DECLARE_DELEGATE_OneParam(FOnGetOtelAuthReaderConfigFullResponse, FGetOtelAuthReaderConfigFullResponse);
