
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogSwitchContextDocument.h"

#include "GetLoglevelContextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLoglevelContextRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FOptionalString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Routing Key", Category="Beam")
	FOptionalString RoutingKey = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetLoglevelContextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetLoglevelContext",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ServiceName,_RoutingKey,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetLoglevelContextRequest* Make(FOptionalString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLoglevelContextSuccess, FBeamRequestContext, Context, UGetLoglevelContextRequest*, Request, UBeamoV2LogSwitchContextDocument*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLoglevelContextError, FBeamRequestContext, Context, UGetLoglevelContextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetLoglevelContextComplete, FBeamRequestContext, Context, UGetLoglevelContextRequest*, Request);

using FGetLoglevelContextFullResponse = FBeamFullResponse<UGetLoglevelContextRequest*, UBeamoV2LogSwitchContextDocument*>;
DECLARE_DELEGATE_OneParam(FOnGetLoglevelContextFullResponse, FGetLoglevelContextFullResponse);
