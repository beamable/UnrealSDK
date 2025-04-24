
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"

#include "GetStandingsGroupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStandingsGroupRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max", Category="Beam")
	FOptionalInt32 Max = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus", Category="Beam")
	FOptionalInt64 Focus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle", Category="Beam")
	FOptionalInt32 Cycle = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalInt32 From = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetStandingsGroupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetStandingsGroup",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Max,_Focus,_Cycle,_From,_ContentId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetStandingsGroupRequest* Make(FString _TournamentId, FOptionalInt32 _Max, FOptionalInt64 _Focus, FOptionalInt32 _Cycle, FOptionalInt32 _From, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsGroupSuccess, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request, UGetStandingsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsGroupError, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStandingsGroupComplete, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request);

using FGetStandingsGroupFullResponse = FBeamFullResponse<UGetStandingsGroupRequest*, UGetStandingsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStandingsGroupFullResponse, FGetStandingsGroupFullResponse);
