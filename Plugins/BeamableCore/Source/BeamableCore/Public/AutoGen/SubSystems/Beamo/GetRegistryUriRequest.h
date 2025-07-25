
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2UriResponse.h"

#include "GetRegistryUriRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRegistryUriRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRegistryUriRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetRegistryUri",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRegistryUriRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRegistryUriSuccess, FBeamRequestContext, Context, UGetRegistryUriRequest*, Request, UBeamoV2UriResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRegistryUriError, FBeamRequestContext, Context, UGetRegistryUriRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRegistryUriComplete, FBeamRequestContext, Context, UGetRegistryUriRequest*, Request);

using FGetRegistryUriFullResponse = FBeamFullResponse<UGetRegistryUriRequest*, UBeamoV2UriResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRegistryUriFullResponse, FGetRegistryUriFullResponse);
