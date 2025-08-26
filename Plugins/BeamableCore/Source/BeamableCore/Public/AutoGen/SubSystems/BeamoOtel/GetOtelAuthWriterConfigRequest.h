
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"

#include "GetOtelAuthWriterConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOtelAuthWriterConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetOtelAuthWriterConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make GetOtelAuthWriterConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetOtelAuthWriterConfigRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelAuthWriterConfigSuccess, FBeamRequestContext, Context, UGetOtelAuthWriterConfigRequest*, Request, UOtelAuthConfig*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOtelAuthWriterConfigError, FBeamRequestContext, Context, UGetOtelAuthWriterConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetOtelAuthWriterConfigComplete, FBeamRequestContext, Context, UGetOtelAuthWriterConfigRequest*, Request);

using FGetOtelAuthWriterConfigFullResponse = FBeamFullResponse<UGetOtelAuthWriterConfigRequest*, UOtelAuthConfig*>;
DECLARE_DELEGATE_OneParam(FOnGetOtelAuthWriterConfigFullResponse, FGetOtelAuthWriterConfigFullResponse);
