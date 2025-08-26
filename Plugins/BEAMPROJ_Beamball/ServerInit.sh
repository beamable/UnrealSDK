#!/usr/bin/env bash

echo "Beginning init.sh script..."

# Hathora default environment variables (these are added by Hathora automatically)
echo "HATHORA_INITIAL_ROOM_CONFIG : $HATHORA_INITIAL_ROOM_CONFIG"
echo "HATHORA_INITIAL_ROOM_ID : $HATHORA_INITIAL_ROOM_ID"
echo "HATHORA_PROCESS_ID : $HATHORA_PROCESS_ID"
echo "HATHORA_APP_ID : $HATHORA_APP_ID"
echo "HATHORA_DEPLOYMENT_ID : $HATHORA_DEPLOYMENT_ID"
echo "HATHORA_BUILD_TAG : $HATHORA_BUILD_TAG"

# These need to be add manually as environment variables (via application's deployment config)
echo "HATHORA_DEV_TOKEN : $HATHORA_DEV_TOKEN"
echo "COMMAND_LINE_ARGS : $COMMAND_LINE_ARGS"

echo "Starting game server..."

./BeamableUnrealServer.sh -beamable-realm-secret="$BEAMABLE_REALM_SECRET" \
  -beamable-customer-override="$BEAMABLE_CUSTOMER_OVERRIDE" \
  -beamable-realm-override="$BEAMABLE_REALM_OVERRIDE" \
  -BeamableDedicatedServerInstanceLobbyId="$HATHORA_INITIAL_ROOM_ID" \
  "$COMMAND_LINE_ARGS"
  