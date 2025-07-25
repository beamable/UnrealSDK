
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DeleteRegistrationRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "DeleteServicesFederationTrafficRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteServicesFederationTrafficRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2DeleteRegistrationRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteServicesFederationTrafficRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteServicesFederationTraffic",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RoutingKey,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteServicesFederationTrafficRequest* Make(FString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesFederationTrafficSuccess, FBeamRequestContext, Context, UDeleteServicesFederationTrafficRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesFederationTrafficError, FBeamRequestContext, Context, UDeleteServicesFederationTrafficRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteServicesFederationTrafficComplete, FBeamRequestContext, Context, UDeleteServicesFederationTrafficRequest*, Request);

using FDeleteServicesFederationTrafficFullResponse = FBeamFullResponse<UDeleteServicesFederationTrafficRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnDeleteServicesFederationTrafficFullResponse, FDeleteServicesFederationTrafficFullResponse);
