
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "PutServicesFederationTrafficRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutServicesFederationTrafficRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2ServiceRegistrationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutServicesFederationTrafficRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PutServicesFederationTraffic",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RoutingKey,_bTrafficFilterEnabled,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutServicesFederationTrafficRequest* Make(FString _ServiceName, FOptionalString _RoutingKey, FOptionalBool _bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutServicesFederationTrafficSuccess, FBeamRequestContext, Context, UPutServicesFederationTrafficRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutServicesFederationTrafficError, FBeamRequestContext, Context, UPutServicesFederationTrafficRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutServicesFederationTrafficComplete, FBeamRequestContext, Context, UPutServicesFederationTrafficRequest*, Request);

using FPutServicesFederationTrafficFullResponse = FBeamFullResponse<UPutServicesFederationTrafficRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutServicesFederationTrafficFullResponse, FPutServicesFederationTrafficFullResponse);
