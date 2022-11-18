
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/LeaveRoomRequestBody.h"
#include "AutoGen/LeaveRoomResponse.h"

#include "DeleteRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaveRoomRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|ChatV2", DisplayName="Beam - Make DeleteRooms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UDeleteRoomsRequest* Make(int64 _ObjectId, FString _RoomId, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoomsSuccess, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request, ULeaveRoomResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoomsError, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteRoomsComplete, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request);

using FDeleteRoomsFullResponse = FBeamFullResponse<UDeleteRoomsRequest*, ULeaveRoomResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteRoomsFullResponse, FDeleteRoomsFullResponse);
