
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/GetRoomsResponse.h"

#include "GetRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|ChatV2", DisplayName="Beam - Make GetRooms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UGetRoomsRequest* Make(int64 _ObjectId, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoomsSuccess, FBeamRequestContext, Context, UGetRoomsRequest*, Request, UGetRoomsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoomsError, FBeamRequestContext, Context, UGetRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRoomsComplete, FBeamRequestContext, Context, UGetRoomsRequest*, Request);

using FGetRoomsFullResponse = FBeamFullResponse<UGetRoomsRequest*, UGetRoomsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRoomsFullResponse, FGetRoomsFullResponse);
